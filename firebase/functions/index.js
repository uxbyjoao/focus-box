const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp();

// Database instances
const firestoreDb = admin.firestore();
const realtimeDb = admin.database();

// Collections & refs
const entriesRef = firestoreDb.collection("entries");
const boxStatusRef = realtimeDb.ref("box_status");
const notificationRef = realtimeDb.ref("last_session_notification");

/**
 * Starts a focus session and logs it to the realtime database
 */
exports.startSession = functions.https.onRequest(async (_, res) => {
  let error, response;
  // Modify box status
  try {
    await boxStatusRef.update({
      is_running: true,
      start: Date.now(),
    });
    response = {
      status: "ok",
      message: "Successfully started session.",
    };
  } catch (err) {
    response = {
      status: "error",
      message: error.message,
    };
  }
  res.send(response);
});

/**
 * Logs the end of a session and records session to Firestore
 */
exports.endSession = functions.https.onRequest(async (req, res) => {
  let response;
  // Push new session to Firestore
  if (req.query.duration) {
    try {
      const snapshot = await boxStatusRef.once("value");
      const val = snapshot.val();
      const newSession = {
        title: val.title,
        start: val.start,
        end: Date.now(),
        duration: req.query.duration,
      };
      const newRef = await entriesRef.add(newSession);
      response = {
        status: "ok",
        message: `Created a new session with id ${newRef.id}`,
      };
    } catch (err) {
      response = {
        status: "error",
        message: err.message,
      };
    }
  } else {
    response = {
      status: "error",
      message: "No duration present in request query.",
    };
  }
  res.send(response);
});

/**
 * Watches for new session entries and resets the box after they're logged
 */
exports.resetBoxStatus = functions.firestore
  .document("/entries/{entryId}")
  .onCreate(() => {
    return boxStatusRef.set({
      is_running: false,
      start: 0,
      title: "",
    });
  });

/**
 * Watches for new session entries and notifies the frontend
 */
exports.notifyNewSessionAdded = functions.firestore
  .document("/entries/{entryId}")
  .onCreate((snapshot, context) => {
    const newEntryVal = snapshot.data();
    return notificationRef.set({
      entry: {
        id: context.params.entryId,
        ...newEntryVal,
      },
      read: false,
    });
  });

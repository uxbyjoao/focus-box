const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp();

const firestoreDb = admin.firestore();
const realtimeDb = admin.database();

const entriesRef = firestoreDb.collection("entries");
const boxStatusRef = realtimeDb.ref("box_status");

exports.startSession = functions.https.onRequest(async (_, res) => {
  let error, response;
  // Modify box status
  try {
    await boxStatusRef.set({
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

exports.resetBoxStatus = functions.firestore
  .document("/entries/{documentId}")
  .onCreate(() => {
    return boxStatusRef.set({
      is_running: false,
      start: 0,
      title: "",
    });
  });

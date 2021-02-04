const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp();

exports.postSession = functions.https.onRequest(async (req, res) => {
  let response;
  if (req.query.duration && req.query.title) {
    const newEntry = {
      start: Date.now() - req.query.duration,
      finish: Date.now(),
      duration: req.query.duration,
      title: req.query.title,
    };
    // Log new session
    const writeResult = await admin
      .firestore()
      .collection("entries")
      .add({ ...newEntry });
    // Stop current session
    await admin.firestore().collection("sessions").doc("current").set({
      started: false,
    });
    response = {
      status: "ok",
      message: `Successfully added new time entry with ID ${writeResult.id}.`,
      payload: newEntry,
    };
  } else {
    response = {
      status: "error",
      message: "No duration present in request query.",
    };
  }
  res.send(response);
});

exports.startSession = functions.https.onRequest(async (_, res) => {
  await admin.firestore().collection("sessions").doc("current").set({
    started: true,
    start_time: Date.now(),
  });
  const response = {
    status: "ok",
    message: "Session start successfully logged to database.",
  };
  res.send(response);
});

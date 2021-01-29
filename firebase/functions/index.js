const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp();

exports.postSession = functions.https.onRequest(async (req, res) => {
  let response;
  if (req.query.duration) {
    const newEntry = {
      start: Date.now() - req.query.duration,
      finish: Date.now(),
      duration: req.query.duration,
    };
    const writeResult = await admin
      .firestore()
      .collection("entries")
      .add({ ...newEntry });
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

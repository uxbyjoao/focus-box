import firebase from "firebase/app";
import "firebase/database";
import "firebase/firestore";

const config = {
  apiKey: process.env.VUE_APP_FIREBASE_APIKEY,
  authDomain: process.env.VUE_APP_FIREBASE_AUTHDOMAIN,
  databaseURL: process.env.VUE_APP_FIREBASE_DATABASEURL,
  projectId: process.env.VUE_APP_FIREBASE_PROJECTID,
  storageBucket: process.env.VUE_APP_FIREBASE_STORAGEBUCKET,
  messagingSenderId: process.env.VUE_APP_FIREBASE_MESSAGINGSENDERID,
  appId: process.env.VUE_APP_FIREBASE_APPID,
};

export const firebaseApp = firebase.initializeApp(config);

export const realtimeDb = firebaseApp.database();
export const firestoreDb = firebaseApp.firestore();

export const boxStatusRef = realtimeDb.ref("box_status");
export const entriesCollection = firestoreDb.collection("entries");
export const lastSessionNotificationRef = realtimeDb.ref(
  "last_session_notification"
);

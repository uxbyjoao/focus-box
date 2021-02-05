<template>
  <div id="app">
    <top-bar></top-bar>
    <tracker box-status="box_status"></tracker>
    <entry-list></entry-list>
  </div>
</template>

<script>
import {
  boxStatusRef,
  prevSessionRef,
  entriesCollection,
} from "./firebase/index";

import TopBar from "./components/TopBar";
import Tracker from "./components/Tracker";
import EntryList from "./components/EntryList";

export default {
  name: "app",

  components: {
    TopBar,
    Tracker,
    EntryList,
  },

  data() {
    return {
      loading: true,
      box_status: {},
      previous_session: {},
      entries: [],
    };
  },

  firebase: {
    box_status: boxStatusRef,
    previous_session: prevSessionRef,
  },

  firestore: {
    entries: entriesCollection,
  },
};
</script>

<style>
</style>

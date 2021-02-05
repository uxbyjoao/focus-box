<template>
  <div id="app">
    <top-bar></top-bar>
    <tracker :box-status="boxStatus"></tracker>
    <entry-list></entry-list>
  </div>
</template>

<script>
import { boxStatusRef, prevSessionRef } from "./firebase/index";

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
      boxStatus: {},
      prevSession: {},
    };
  },

  firebase: {
    boxStatus: boxStatusRef,
    prevSession: prevSessionRef,
  },

  methods: {
    async handleNewPrevSession(val) {
      if (val.notification_read === false) {
        let title;

        if (val.data.title === "") {
          title = "Untitled Session";
        } else {
          title = val.data.title;
        }

        this.$buefy.snackbar.open({
          type: "is-success",
          message: `Added ${title} with duration of ${val.data.duration}.`,
          position: "is-bottom",
        });

        await prevSessionRef.update({ notification_read: true });
      }
    },
  },

  watch: {
    prevSession: "handleNewPrevSession",
  },
};
</script>

<style>
body {
  background-color: #f5f5f5;
  height: 100vh;
}
</style>

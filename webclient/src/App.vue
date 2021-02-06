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

import { formatEntryDuration, formatEntryTitle } from "./mixins/index";

export default {
  name: "app",

  components: {
    TopBar,
    Tracker,
    EntryList,
  },

  mixins: [formatEntryTitle, formatEntryDuration],

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
        const title = this.formatEntryTitle(val.data.title);
        const duration = this.formatEntryDuration(val.data.start, val.data.end);
        this.$buefy.snackbar.open({
          type: "is-success",
          message: `Added "${title}" with duration of ${duration}.`,
          position: "is-bottom",
          duration: 10000,
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

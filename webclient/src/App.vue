<template>
  <div id="app">
    <top-bar></top-bar>
    <tracker-hero></tracker-hero>
    <entry-list></entry-list>
  </div>
</template>

<script>
import { lastSessionNotificationRef } from "./firebase/index";

import TopBar from "./components/TopBar";
import TrackerHero from "./components/TrackerHero";
import EntryList from "./components/EntryList";

export default {
  name: "app",
  components: {
    TopBar,
    TrackerHero,
    EntryList,
  },

  data() {
    return {
      last_session_notification: {
        entry: {
          title: "",
        },
        read: true,
      },
    };
  },

  computed: {
    session_title_computed() {
      return this.last_session_notification.entry.title === ""
        ? "Untitled Session"
        : this.last_session_notification.entry.title;
    },
  },

  firebase: {
    last_session_notification: lastSessionNotificationRef,
  },

  methods: {
    handleSnackbarOpen(val) {
      if (!val.read) {
        this.$buefy.snackbar.open({
          type: "is-primary",
          message: `Finished ${this.session_title_computed} after ${val.entry.duration}.`,
          position: "is-bottom",
          indefinite: true,
          onAction: async () => {
            await lastSessionNotificationRef.update({ read: true });
          },
        });
      }
    },
  },

  watch: {
    last_session_notification: {
      immediate: true,
      handler: "handleSnackbarOpen",
    },
  },
};
</script>

<style>
</style>

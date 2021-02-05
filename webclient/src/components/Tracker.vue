<template>
  <section
    class="section section-tracker has-text-centered has-background-white"
  >
    <!-- Session is running -->
    <session-in-progress
      v-if="boxStatus.has_phone"
      :title="boxStatus.title"
      :start="boxStatus.start"
    ></session-in-progress>
    <!-- Session is not running, but ready from frontend -->
    <new-session-ready
      v-else-if="ready"
      :title="title"
      @cancel-next-session="handleCancelNextSession"
    ></new-session-ready>
    <!--  -->
    <new-session-form
      v-else
      :title="title"
      @ready-next-session="handleReadyNextSession"
    ></new-session-form>
  </section>
</template>

<script>
import { boxStatusRef } from "../firebase/index";

import SessionInProgress from "./SessionInProgress";
import NewSessionReady from "./NewSessionReady";
import NewSessionForm from "./NewSessionForm";

export default {
  name: "tracker",

  components: { SessionInProgress, NewSessionReady, NewSessionForm },

  props: ["boxStatus", "nextSession"],

  data() {
    return {
      title: "",
      ready: false,
    };
  },

  methods: {
    handleBoxStatusChange(val) {
      if (val.has_phone === true) {
        this.ready = false;
        this.title = "";
      }
    },

    async handleCancelNextSession() {
      this.ready = false;
      this.title = "";
      return await boxStatusRef.update({ title: "" });
    },

    async handleReadyNextSession(title) {
      this.ready = true;
      this.title = title;
      if (title) {
        return await boxStatusRef.update({ title });
      }
    },
  },

  watch: {
    boxStatus: "handleBoxStatusChange",
  },
};
</script>

<style>
.section-tracker {
  height: 550px;
}

.section-tracker .columns {
  /* background-color: red; */
  height: 100%;
}

.section-tracker .columns .interior {
  /* background-color: green; */
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}
</style>
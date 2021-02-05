<template>
  <div class="columns">
    <div
      class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
    >
      <div class="interior">
        <div>
          <h1 class="title is-size-2">Focus.</h1>
        </div>
        <div>
          <p>Close the box and focus on</p>
          <h1 class="is-size-3">{{ computed_title }}</h1>
        </div>
        <session-clock :start="start"></session-clock>
        <b-notification :closable="false" type="is-success is-light">
          <p class="is-size-5">
            When you're done, remove the phone from the box.
          </p>
        </b-notification>
      </div>
    </div>
  </div>
</template>

<script>
import SessionClock from "./SessionClock";

export default {
  name: "session-in-progress",

  components: { SessionClock },

  props: ["title", "start"],

  computed: {
    computed_title() {
      if (!this.title || this.title.length === 0) {
        return "Untitled Session";
      } else return this.title;
    },
  },
};
</script>

<style>
</style>
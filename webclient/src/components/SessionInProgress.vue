<template>
  <div class="columns" :key="this.intervalId">
    <div
      class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
    >
      <div class="interior">
        <div>
          <h1 class="title is-size-2">Focus.</h1>
        </div>
        <div>
          <p>Close the box and focus on</p>
          <h1 class="is-size-3">{{ title | entry_title }}</h1>
        </div>
        <div>
          <p class="is-size-2">{{ duration }}</p>
        </div>
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
import { intervalToDuration } from "date-fns";

export default {
  name: "session-in-progress",

  props: ["title", "start"],

  data() {
    return {
      now: Date.now(),
      intervalId: null,
    };
  },

  computed: {
    duration() {
      // TODO: Optimize this, please
      const prependZero = (num) =>
        String(num).length < 2 ? `0${num}` : `${num}`;
      const duration = intervalToDuration({
        start: this.start,
        end: this.now,
      });
      const hours = prependZero(duration.hours);
      const minutes = prependZero(duration.minutes);
      const seconds = prependZero(duration.seconds);
      return `${hours}:${minutes}:${seconds}`;
    },
  },

  methods: {
    incrementNow() {
      this.now += 1000;
    },
  },

  created() {
    this.intervalId = setInterval(this.incrementNow, 1000);
  },

  destroyed() {
    clearInterval(this.intervalId);
  },
};
</script>

<style>
</style>
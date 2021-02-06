<template>
  <div class="columns">
    <div
      class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
    >
      <div class="interior">
        <div>
          <h1 class="title is-size-2">You are ready.</h1>
        </div>
        <div>
          <p>You have now pledged to focus on</p>
          <h1 class="is-size-3">{{ title | entry_title }}</h1>
        </div>
        <b-notification :closable="false" type="is-success is-light">
          <p class="is-size-5">
            Put your phone in the box, and the session will start automatically.
          </p>
        </b-notification>
        <b-button
          type="is-danger is-light is-large"
          @click="emitCancelNextSession"
          >Abort, captain!</b-button
        >
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "new-session-ready",

  props: ["title"],

  methods: {
    emitCancelNextSession() {
      return this.$emit("cancel-next-session");
    },
  },
};
</script>

<style>
</style>
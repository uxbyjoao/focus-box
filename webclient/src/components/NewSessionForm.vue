<template>
  <div class="columns" @keydown.enter="emitReadyNextSession">
    <div
      class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
    >
      <div class="interior">
        <h1 class="title is-size-2">Ready to focus?</h1>
        <p class="is-size-5">
          Write down your next task, make a pledge to yourself to focus and put
          your phone in the box.
        </p>
        <div>
          <b-field label="What do you want to focus on now?">
            <b-input
              size="is-medium"
              placeholder="Do user research"
              icon-right="close-circle"
              icon-right-clickable
              v-model="local_title"
              @icon-right-click="clearTitle"
            ></b-input>
          </b-field>
        </div>
        <div>
          <b-button
            type="is-primary is-medium"
            expanded
            @click="emitReadyNextSession"
            >I'm ready to put my phone away.</b-button
          >
          <p class="is-size-7">
            Hint: You can also just drop the phone in the box and name your task
            later. Try it!
          </p>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "new-session-form",

  data() {
    return {
      local_title: this.title,
    };
  },

  methods: {
    clearTitle() {
      this.local_title = "";
    },

    emitReadyNextSession() {
      return this.$emit("ready-next-session", this.local_title);
    },
  },
};
</script>

<style>
</style>
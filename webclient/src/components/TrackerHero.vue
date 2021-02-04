<template>
  <section class="section">
    <div class="container has-text-centered">
      <div class="session-form">
        <div class="session-form-title">
          <h1 class="title is-size-2">Ready to focus?</h1>
          <p class="is-size-5">
            Write down your next task, make a pledge to yourself to focus and
            put your phone in the box.
          </p>
        </div>
        <b-field label="What do you want to focus on now?">
          <b-input
            size="is-medium"
            placeholder="Do user research"
            icon-right="close-circle"
            icon-right-clickable
            v-model="title"
            @icon-right-click="clear"
          ></b-input>
        </b-field>
        <b-button type="is-primary" expanded
          >I'm ready to put my phone away.</b-button
        >
        <p class="is-size-7 session-form-help">
          Hint: You can also just drop the phone in the box and name your task
          later. Try it!
        </p>
      </div>
      <div class="sessions-indicator">
        <p class="has-text-weight-medium">See older sessions</p>
        <b-icon icon="chevron-down"></b-icon>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  data() {
    return {
      title: "",
    };
  },
  methods: {
    clear() {
      this.title = "";
    },
  },
};
</script>

<style>
.container {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  height: 480px;
}

.session-form > .session-form-title {
  margin-bottom: 2rem;
}

.session-form > .session-form-help {
  margin-top: 0.5rem;
}
</style>
<template>
  <section class="section">
    <div class="container has-text-centered">
      <div class="session-form">
        <div class="session-form-title">
          <h1 class="title is-size-1">Ready to focus?</h1>
          <p class="is-size-4">
            Write down your next task on the box below and click the magic focus
            button.
          </p>
        </div>
        <b-field>
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
      </div>
      <div class="sessions-indicator">
        <span>See older sessions below</span>
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
  height: 450px;
}

.session-form > .session-form-title {
  margin-bottom: 2rem;
}
</style>
<template>
  <div>
    <section class="section section-tracker has-text-centered">
      <!-- Hasn't synced Firebase yet -->
      <div v-if="box_status === null" class="container">
        <b-loading active></b-loading>
      </div>

      <!-- Session is not running, not ready to start -->
      <div class="columns" v-else-if="!box_status.is_running && !session_ready">
        <div
          class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
        >
          <div class="session-form" @keypress.enter="makeSessionReady">
            <div class="session-form-title">
              <h1 class="title is-size-2">Ready to focus?</h1>
              <p class="is-size-5">
                Write down your next task, make a pledge to yourself to focus
                and put your phone in the box.
              </p>
            </div>
            <b-field label="What do you want to focus on now?">
              <b-input
                size="is-medium"
                placeholder="Do user research"
                icon-right="close-circle"
                icon-right-clickable
                v-model="session_title"
                @icon-right-click="clearTitle"
              ></b-input>
            </b-field>
            <b-button
              type="is-primary is-medium"
              @click="makeSessionReady"
              expanded
              >I'm ready to put my phone away.</b-button
            >
            <p class="is-size-7 session-form-help">
              Hint: You can also just drop the phone in the box and name your
              task later. Try it!
            </p>
          </div>
          <div class="sessions-indicator">
            <p class="has-text-weight-medium">See older sessions</p>
            <b-icon icon="chevron-down"></b-icon>
          </div>
        </div>
      </div>

      <!-- Session is not running, ready to start -->
      <div class="columns" v-else-if="!box_status.is_running && session_ready">
        <div
          class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
        >
          <div class="session-form-title">
            <h1 class="title is-size-2">You are ready.</h1>
          </div>
          <div>
            <p>You have now pledged to focus on</p>
            <h1 class="is-size-3">{{ session_title_computed }}</h1>
          </div>
          <b-notification :closable="false" type="is-success is-light">
            <p class="is-size-5">
              Put your phone in the box, and the session will start
              automatically.
            </p>
          </b-notification>
          <b-button type="is-danger is-light is-large" @click="abortSession"
            >Abort, captain!</b-button
          >
        </div>
      </div>

      <!-- Session is running -->
      <div class="columns" v-else>
        <div
          class="column is-6-desktop is-offset-3-desktop is-8-tablet is-offset-2-tablet"
        >
          <div class="session-form-title">
            <h1 class="title is-size-2">Focus.</h1>
          </div>
          <div>
            <h1 class="is-size-3">{{ session_title_computed }}</h1>
            <session-clock :start-time="1612535492651"></session-clock>
          </div>
          <b-notification :closable="false" type="is-success is-light">
            <p class="is-size-5">
              When you're done, remove the phone from the box.
            </p>
          </b-notification>
        </div>
      </div>
    </section>
    <b-loading v-model="loading"></b-loading>
  </div>
</template>

<script>
import { boxStatusRef } from "../firebase/index";

import SessionClock from "./SessionClock.vue";

export default {
  name: "tracker-hero",
  components: {
    SessionClock,
  },

  data() {
    return {
      loading: false,
      session_title: "",
      session_ready: false,
      box_status: null,
    };
  },

  firebase: {
    box_status: boxStatusRef,
  },

  computed: {
    session_title_computed() {
      return this.session_title === ""
        ? "Untitled Session"
        : this.session_title;
    },
  },

  methods: {
    clearTitle() {
      this.session_title = "";
    },
    async makeSessionReady() {
      this.loading = true;
      try {
        boxStatusRef.update({ title: this.session_title });
        this.loading = false;
        this.session_ready = true;
      } catch (error) {
        this.loading = false;
        console.log(error);
      }
    },
    abortSession() {
      this.session_ready = false;
    },
  },
};
</script>

<style>
.section-tracker {
  height: 560px;
}

.section-tracker > .columns {
  height: 100%;
}

.section-tracker > .columns > .column {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}

.session-form > .session-form-title {
  margin-bottom: 2rem;
}

.session-form > .session-form-help {
  margin-top: 0.5rem;
}
</style>
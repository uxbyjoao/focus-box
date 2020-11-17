<template>
  <div>
    <h1>Hello World!</h1>
    <p>This is a message from the parent: {{ msg }}</p>
    <p><strong>LED Status:</strong> {{ led_status }}</p>
    <button @click="toggleLed">Toggle LED in ESP8266</button>
  </div>
</template>

<script>
import { db } from "../firebase";

export default {
  name: "HelloWorld",
  props: {
    msg: String,
  },
  data() {
    return {
      res: "",
    };
  },
  firebase: {
    res: db.ref("/"),
  },
  methods: {
    toggleLed() {
      this.$firebaseRefs.res
        .update({ led_status: !this.res.led_status })
        .then(() => {
          console.log("led status updated from client.");
        });
    },
  },
  computed: {
    led_status() {
      return this.res.led_status ? "on" : "off";
    },
  },
};
</script>

<style scoped>
button {
  background-color: purple;
  color: white;
  padding: 0.7rem 1rem;
  border-width: 0;
  border-radius: 6px;
  transition: background-color 0.2s;
  cursor: pointer;
}

button:hover {
  background-color: plum;
}
</style>

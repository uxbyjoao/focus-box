<template>
  <div>{{ time }}</div>
</template>

<script>
export default {
  name: "session-clock",

  props: ["start"],

  computed: {
    time() {
      return this.start;
    },
  },
};
</script>

<style>
</style>
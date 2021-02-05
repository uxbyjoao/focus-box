<template>
  <section class="section has-text-centered">
    <new-session-ready></new-session-ready>
  </section>
</template>

<script>
// import NewSessionForm from "./NewSessionForm";
import NewSessionReady from "./NewSessionReady";

export default {
  name: "tracker",
  components: { NewSessionReady },
};
</script>

<style>
</style>
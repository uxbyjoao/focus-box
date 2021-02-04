<template>
  <div id="app">
    <top-bar></top-bar>
    <tracker-hero></tracker-hero>
    <entry-list></entry-list>
  </div>
</template>

<script>
import TopBar from "./components/TopBar";
import TrackerHero from "./components/TrackerHero";
import EntryList from "./components/EntryList";

export default {
  name: "App",
  components: {
    TopBar,
    TrackerHero,
    EntryList,
  },
};
</script>

<style>
</style>

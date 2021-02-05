<template>
  <section class="section has-background-light">
    <entry-card
      v-for="entry in entries"
      :key="entry.id"
      :entry="entry"
    ></entry-card>
  </section>
</template>

<script>
import EntryCard from "./EntryCard";

const DUMMY_ENTRIES = [
  {
    id: "8ag7hr09235",
    start: Date.now(),
    finish: Date.now(),
    duration: 12387987345,
    title: "Front-End for Focus Box",
  },
  {
    id: "8ag7hr09235",
    start: Date.now(),
    finish: Date.now(),
    duration: 12387987345,
    title: "Front-End for Focus Box",
  },
];

export default {
  components: { EntryCard },
  data() {
    return {
      entries: DUMMY_ENTRIES,
    };
  },
};
</script>

<style>
.card-content > .card-content-time > .card-content-time-hours {
  display: flex;
  width: 100%;
  justify-content: space-between;
}

.card-content > .card-content-title {
  margin-top: 0.4rem;
}

.card-content > .card-content-controls {
  margin-top: 0.8rem;
}
</style>
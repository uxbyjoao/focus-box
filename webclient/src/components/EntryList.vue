<template>
  <section v-if="entries.length > 0" class="section has-background-light">
    <entry-card
      v-for="entry in entries"
      :key="entry.id"
      :entry="entry"
    ></entry-card>
  </section>
  <section v-else class="section has-background-light has-text-centered">
    <p class="is-size-4">No recorded sessions yet.</p>
    <p>Scroll up to get started!</p>
  </section>
</template>

<script>
import EntryCard from "./EntryCard";

import { entriesCollection } from "../firebase/index";

export default {
  name: "entry-list",
  components: { EntryCard },
  data() {
    return {
      entries: [],
    };
  },
  firestore: {
    entries: entriesCollection,
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
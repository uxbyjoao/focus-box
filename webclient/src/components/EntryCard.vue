<template>
  <div class="card card-entry">
    <div class="card-content">
      <div class="card-content-time">
        <div class="card-content-time-hours">
          <span>{{ entry.start }} → {{ entry.finish }}</span>
          <span>{{ entry.duration }}</span>
        </div>
      </div>
      <div class="card-content-title">
        <h3 class="is-size-5 has-text-weight-semibold">
          {{ entry.title }}
        </h3>
      </div>
      <div class="card-content-controls">
        <b-button type="is-text" size="is-small" icon-left="edit"
          >Edit</b-button
        >
        <b-button type="is-text" size="is-small" icon-left="delete"
          >Delete</b-button
        >
      </div>
    </div>
  </div>
</template>

<script>
export default {
  props: ["entry"],
};
</script>

<style>
.card-entry {
  margin-bottom: 1.25rem;
}
</style>
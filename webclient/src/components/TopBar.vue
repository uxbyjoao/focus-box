<template>
  <b-navbar fixed-top>
    <template #brand>
      <b-navbar-item tag="router-link" :to="{ path: '/' }">
        <h1 class="is-size-4"><strong>Focus</strong>Box</h1>
      </b-navbar-item>
    </template>

    <template #end>
      <b-navbar-item> About </b-navbar-item>
      <b-navbar-item tag="span">v0.0.1</b-navbar-item>
    </template>
  </b-navbar>
</template>

<script>
export default {
  name: "top-bar",
};
</script>

<style>
</style>
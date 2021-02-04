<template>
  <b-navbar fixed-top>
    <template #brand>
      <b-navbar-item tag="router-link" :to="{ path: '/' }">
        <h1 class="is-size-4"><strong>Focus</strong>Box</h1>
      </b-navbar-item>
    </template>

    <template #end>
      <b-navbar-item tag="div">
        <p>Created by <strong>João Gomes</strong></p>
        <p>v0.0.1</p>
      </b-navbar-item>
    </template>
  </b-navbar>
</template>

<script>
export default {};
</script>

<style>
</style>
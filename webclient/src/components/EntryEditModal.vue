<template>
  <div class="modal-card" style="witdth: auto; margin: 0 auto">
    <header class="modal-card-head">
      <p class="modal-card-title">Editing "{{ entry.title | entry_title }}"</p>
    </header>
    <section class="modal-card-body">
      <b-field label="Entry Title">
        <b-input v-model="title" placeholder="Entry Title"></b-input>
      </b-field>
      <b-field grouped group->
        <b-field label="Start Date & Time" expanded>
          <b-datetimepicker
            v-model="start"
            icon="calendar"
            expanded
            disabled
          ></b-datetimepicker>
        </b-field>
        <b-field label="End Date & Time" expanded>
          <b-datetimepicker
            v-model="end"
            icon="calendar"
            expanded
            disabled
          ></b-datetimepicker>
        </b-field>
      </b-field>
      <p class="is-size-7 has-text-danger">
        Editing dates and times is not supported in v0.1. Sorry!
      </p>
    </section>
    <footer class="modal-card-foot">
      <b-button label="Cancel" @click="handleClose" />
      <b-button label="Ok" type="is-primary" @click="handleOk" />
    </footer>
  </div>
</template>

<script>
export default {
  name: "entry-edit-modal",
  props: ["entry"],

  data() {
    return {
      title: this.entry.title,
      start: new Date(this.entry.start),
      end: new Date(this.entry.end),
    };
  },

  methods: {
    handleOk() {
      const nextEntry = {
        id: this.entry.id,
        title: this.title,
        start: this.entry.start,
        end: this.entry.end,
        duration: this.entry.duration,
      };
      this.$emit("ok", nextEntry);
      return this.handleClose();
    },

    handleClose() {
      return this.$emit("close");
    },
  },
};
</script>

<style>
</style>
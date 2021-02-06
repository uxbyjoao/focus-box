<template>
  <section v-if="entries.length > 0" class="section has-background-light">
    <h2 class="subtitle has-text-centered">Past Sessions</h2>
    <div class="columns">
      <div class="column is-10-desktop is-offset-1-desktop is-12-tablet">
        <b-table
          :data="entries"
          default-sort-direction="desc"
          default-sort="end"
        >
          <b-table-column field="title" label="Title" v-slot="props">
            <strong>{{ props.row.title | entry_title }}</strong>
          </b-table-column>
          <b-table-column
            sortable
            centered
            field="start"
            label="Start Time"
            v-slot="props"
          >
            {{ props.row.start | entry_date }}
          </b-table-column>
          <b-table-column
            sortable
            centered
            field="end"
            label="End Time"
            v-slot="props"
          >
            {{ props.row.end | entry_date }}
          </b-table-column>
          <b-table-column
            sortable
            centered
            field="duration"
            label="Duration"
            v-slot="props"
          >
            {{ props.row.duration | entry_duration }}
          </b-table-column>
          <b-table-column width="100" v-slot="props">
            <div class="buttons">
              <b-button
                size="is-small"
                type="is-light"
                icon-right="pencil"
                @click="handleOpenEditModal(props.row)"
              ></b-button>
              <b-button
                size="is-small"
                type="is-danger is-light"
                icon-right="close"
                @click="handleDeleteEntry(props.row)"
              ></b-button>
            </div>
          </b-table-column>
        </b-table>
      </div>
    </div>
    <b-modal
      v-model="edit_modal.is_open"
      had-modal-card
      trap-focus
      aria-role="dialog"
      aria-label="Entry Edit Modal"
      aria-modal
    >
      <template #default="props">
        <entry-edit-modal
          :entry="edit_modal.entry"
          @close="props.close"
          @ok="handleCommitEntryEdit"
        ></entry-edit-modal>
      </template>
    </b-modal>
  </section>
  <section v-else class="section has-background-light has-text-centered">
    <p class="is-size-4">No recorded sessions yet.</p>
    <p>Read the instructions above to get started!</p>
  </section>
</template>

<script>
import EntryEditModal from "./EntryEditModal";
import { formatEntryTitle } from "../mixins/index";

import { entriesCollection } from "../firebase/index";

export default {
  name: "entry-list",

  components: { EntryEditModal },

  mixins: [formatEntryTitle],

  data() {
    return {
      entries: [],
      edit_modal: {
        is_open: false,
        entry: {},
      },
    };
  },

  firestore: {
    entries: entriesCollection,
  },

  methods: {
    handleOpenEditModal(entry) {
      this.edit_modal.entry = entry;
      this.edit_modal.is_open = true;
    },

    async handleCommitEntryEdit(nextEntry) {
      const { title, start, end, duration, id } = nextEntry;
      try {
        entriesCollection.doc(id).update({
          title,
          start,
          end,
          duration,
        });
        this.$buefy.toast.open({
          message: "Successfully updated entry.",
          position: "is-bottom",
        });
      } catch (error) {
        this.$buefy.toast.open({
          message: "Couldn't update entry. Check your connection.",
          type: "is-warning",
          position: "is-bottom",
        });
      }
    },

    handleDeleteEntry(entry) {
      let title = this.formatEntryTitle(entry.title);
      this.$buefy.dialog.confirm({
        title: "Deleting Focus Entry",
        message: `This will <strong>delete "${title}"</strong>. This operation is <strong>irreversible</strong>. Are you sure?`,
        confirmText: "Delete Entry",
        type: "is-danger",
        hasIcon: true,
        onConfirm: async function () {
          try {
            entriesCollection.doc(entry.id).delete();
            this.$buefy.toast.open({
              message: `Successfully deleted "${title}".`,
              position: "is-bottom",
            });
          } catch (error) {
            this.$buefy.toast.open({
              message: "Couldn't delete entry. Check your connection.",
              type: "is-warning",
              position: "is-bottom",
            });
          }
        },
      });
    },
  },
};
</script>

<style>
</style>
/**
 * Method to format titles
 */
export const formatEntryTitle = {
  methods: {
    formatEntryTitle(title) {
      if (!title || title.length === 0) {
        return "Untitled Session";
      } else return title;
    },
  },
};

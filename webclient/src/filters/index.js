import { lightFormat } from "date-fns";

/**
 * Global filters
 */
export const appFilters = [
  // Formats entry titles
  {
    id: "entry_title",
    definition: function(title) {
      if (!title || title.length === 0) {
        return "Untitled Session";
      } else return title;
    },
  },
  //   Formats entry dates
  {
    id: "entry_date",
    definition: function(date) {
      const dateObj = new Date(date);
      return lightFormat(dateObj, "HH:mm:ss dd/MM/yyyy");
    },
  },
  //   Formats entry durations
  {
    id: "entry_duration",
    definition: function(ms) {
      // Thanks, Stackoverflow! :)
      let hours = ms / (1000 * 60 * 60);
      let absoluteHours = Math.floor(hours);
      let h = absoluteHours > 9 ? absoluteHours : "0" + absoluteHours;
      let minutes = (hours - absoluteHours) * 60;
      let absoluteMinutes = Math.floor(minutes);
      let m = absoluteMinutes > 9 ? absoluteMinutes : "0" + absoluteMinutes;
      let seconds = (minutes - absoluteMinutes) * 60;
      let absoluteSeconds = Math.floor(seconds);
      let s = absoluteSeconds > 9 ? absoluteSeconds : "0" + absoluteSeconds;
      return h + ":" + m + ":" + s;
    },
  },
];

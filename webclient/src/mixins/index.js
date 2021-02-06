import { intervalToDuration } from "date-fns";

/**
 * Format entry titles
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

/**
 * Format entry durations
 */
export const formatEntryDuration = {
  methods: {
    formatEntryDuration(start, end) {
      // TODO: Optimize this, please
      const prependZero = (num) =>
        String(num).length < 2 ? `0${num}` : `${num}`;

      const duration = intervalToDuration({ start, end });

      const { hours, minutes, seconds } = duration;

      const strHours = prependZero(hours);
      const strMinutes = prependZero(minutes);
      const strSeconds = prependZero(seconds);

      return `${strHours}:${strMinutes}:${strSeconds}`;
    },
  },
};

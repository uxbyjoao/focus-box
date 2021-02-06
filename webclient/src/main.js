import Vue from "vue";
import Buefy from "buefy";
import "buefy/dist/buefy.css";

import App from "./App.vue";

import { rtdbPlugin, firestorePlugin } from "vuefire";

Vue.config.productionTip = false;

Vue.use(rtdbPlugin);
Vue.use(firestorePlugin);
Vue.use(Buefy);

// Global filter for formatting entry titles
Vue.filter("entry_title", function(title) {
  if (!title || title.length === 0) {
    return "Untitled Session";
  } else return title;
});

new Vue({
  render: (h) => h(App),
}).$mount("#app");

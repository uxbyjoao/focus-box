import Vue from "vue";
import Buefy from "buefy";
import { rtdbPlugin, firestorePlugin } from "vuefire";
import "buefy/dist/buefy.css";

import { appFilters } from "./filters/index";
import App from "./App.vue";

Vue.config.productionTip = false;

const appPlugins = [rtdbPlugin, firestorePlugin, Buefy];

appPlugins.forEach((plugin) => Vue.use(plugin));
appFilters.forEach((filter) => Vue.filter(filter.id, filter.definition));

new Vue({
  render: (h) => h(App),
}).$mount("#app");

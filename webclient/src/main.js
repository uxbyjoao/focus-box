import Vue from "vue";
import Buefy from "buefy";
import "buefy/dist/buefy.css";

import App from "./App.vue";

import { rtdbPlugin } from "vuefire";

Vue.config.productionTip = false;

Vue.use(rtdbPlugin);
Vue.use(Buefy);

new Vue({
  render: (h) => h(App),
}).$mount("#app");

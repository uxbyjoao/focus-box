import Vue from "vue";
import Buefy from "buefy";

// import "./styles.scss";

import App from "./App.vue";

import { rtdbPlugin, firestorePlugin } from "vuefire";

Vue.config.productionTip = false;

Vue.use(rtdbPlugin);
Vue.use(firestorePlugin);
Vue.use(Buefy);

new Vue({
  render: (h) => h(App),
}).$mount("#app");

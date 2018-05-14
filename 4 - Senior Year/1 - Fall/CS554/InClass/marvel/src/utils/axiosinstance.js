import axios from "axios";

const apiRoot = `https://gateway.marvel.com:443/v1/public/`;
const apiKey = `&apikey=47c987fd4cebc92483b7a12b00a12ef5`;
//const url = `${apiRoot}characters?nameStartsWith=${searchQuery}&apikey=${apiKey}`;

const instance = axios.create();

instance.interceptors.request.use(function (config) {
    console.log(config);
    config.url = `${apiRoot}${config.url}${apiKey}`;
    return config;
}, function (error) {
    console.log(error);
    return Promise.reject(error);
});

export default instance;
import axios from '@/utils/axios' // 导入axios

const api_all = {
    map_start() {
        return axios({
            url: '/api/map/start/',
            method: 'GET'
        })
    },
    append_wall(x,y) {
        return axios({
            url: '/api/map/add_wall/',
            method: 'POST',
            data: {
                "x":x,
                "y":y,
            }
        })
    }
};

export default api_all // 导出 api_all

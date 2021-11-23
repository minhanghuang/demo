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
    },
    delete_wall(x,y) {
        return axios({
            url: '/api/map/del_wall/',
            method: 'POST',
            data: {
                "x":x,
                "y":y,
            }
        })
    },
    get_walls() {
        return axios({
            url: '/api/map/get_walls/',
            method: 'GET'
        })
    },
    get_base_map() {
        return axios({
            url: '/api/map/get-geojson/',
            method: 'GET'
        })
    },
    nearest_lane(x,y,type) {
        if (x == null || y == null) {
        } else  {
            return axios({
                url: '/api/map/nearest-point/',
                method: 'POST',
                data: {
                    "x":x,
                    "y":y,
                    "type":type,
                }
            })
        }
    },
    path_planning(way_points) {
        if (way_points == null) {

        } else {
            return axios({
                url: '/api/map/planning/',
                method: 'POST',
                data: {
                    "way_points":way_points,
                }
            })
        }
    },
    local_map(x,y) {
        if (x !== 0 && x !== 0) {
            return axios({
                url: '/api/map/local/',
                method: 'POST',
                data: {
                    "x":x,
                    "y":y
                }
            })
        }
    },
    switch_file_path(p) {
        if (p !== '') {
            return axios({
                url: '/api/map/switch/',
                method: 'POST',
                data: {
                    "path":p
                }
            })
        }
    }

};

export default api_all // 导出 api_all

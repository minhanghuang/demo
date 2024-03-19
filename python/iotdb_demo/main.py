from iotdb.Session import Session
from iotdb.utils.IoTDBConstants import TSDataType
from iotdb.utils.Tablet import Tablet


class IoTDBConnection:
    def __init__(
            self,
            host="127.0.0.1",
            port="6667",
            user="root",
            password="root") -> None:
        self.__session = Session(
            host=host,
            port=port,
            user=user,
            password=password,
            zone_id="UTC+8",
        )
        self.__session.open(False)

    def close(self):
        return self.__session.close()

    def query(self, sql: str):
        return self.__session.execute_query_statement(sql)

    def non_query(self, sql: str):
        return self.__session.execute_non_query_statement(sql)

    def insert(self, tablet: Tablet):
        return self.__session.insert_tablet(tablet)

    def __dir__(self):
        self.__session.close()


def main():
    conn = IoTDBConnection()

    # 写
    measurements = [
        "create_time",
        "an_shui",
        "two_temperature",
        "head_coal",
        "kiln_fire",
        "kiln_temperature"
    ]
    data_types = [
        TSDataType.TEXT,
        TSDataType.DOUBLE,
        TSDataType.DOUBLE,
        TSDataType.DOUBLE,
        TSDataType.DOUBLE,
        TSDataType.DOUBLE
    ]
    values = [
        ["2023-08-18 18:06:00", 10, 1101, 15.1, 121.1, 1450],
        ["2023-08-18 18:07:00", 10, 1101, 15.1, 121.1, 1450],
        ["2023-08-18 18:07:00", 10, 1101, 15.1, 121.1, 1450],
        ["2023-08-18 18:07:00", 10, 1101, 15.1, 121.1, 1450],
    ]
    timestamps = [1, 2, 3, 4]

    tablet = Tablet(
        device_id="root.minite.tags_offline",  # 存储组
        measurements=measurements,
        data_types=data_types,
        values=values,
        timestamps=timestamps
    )

    conn.insert(tablet=tablet)

    # 读
    print("--- 读取所有数据")
    sql = "select * from root.minite.tags_offline"
    result = conn.query(sql=sql)  # 所有数据
    df = result.todf()
    print(df.head())

    for row in df.itertuples():
        print(f"row: {row}")

    print("--- 读取数据")
    sql = "select * from root.minite.tags_offline where time >= 1 and time < 3"
    result = conn.query(sql=sql)  # 所有数据
    df = result.todf()
    print(df.head())

    # 删除
    print("--- 删除数据")
    sql = "delete from root.minite.tags_offline where time >= 1 AND time < 3"
    conn.non_query(sql=sql)
    sql = "select * from root.minite.tags_offline"
    result = conn.query(sql=sql)
    df = result.todf()
    print(df.head())

    print("--- 删除存储组")
    sql = "delete storage group root.minite"
    conn.non_query(sql=sql)
    sql = "select * from root.minite.tags_offline"
    result = conn.query(sql=sql)
    df = result.todf()
    print(df.head())


if __name__ == "__main__":
    main()

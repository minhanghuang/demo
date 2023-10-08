import sqlite3


class SQL3(object):

    def __init__(self, path):
        self.path = path
        self.connect = sqlite3.connect(self.path)
        self.cursor = self.connect.cursor()

    def __del__(self):
        self.cursor.close()

    def create_table(self):
        self.cursor.execute("""
        Drop table if exists User
        """)
        self.cursor.execute("""
        CREATE table if not exists User
            (ID INTEGER PRIMARY KEY AUTOINCREMENT,
            NAME            TEXT   NOT NULL,
            AGE             INT    NOT NULL);
        """)

        self.connect.commit()
        return None

    def insert(self):
        self.cursor.execute("""
            INSERT INTO User (NAME, AGE) VALUES ('Trunk', 5)
        """)
        self.cursor.execute("""
            INSERT INTO User (NAME, AGE) VALUES ('Master', 3)
        """)
        self.connect.commit()
        return None

    def update(self):
        self.cursor.execute("""
        UPDATE User Set age=100 where name = 'Master'
        """)
        self.connect.commit()
        return None

    def get(self):
        self.cursor.execute("""
        select * from User
        """)
        print(self.cursor.fetchall())
        return None


if __name__ == '__main__':
    print("Hello SQLite3")
    sql = SQL3("test.db")
    sql.create_table()
    sql.insert()
    sql.update()
    sql.get()

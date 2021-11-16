#include <iostream>
#include <sqlite3.h>
#include <nlohmann/json.hpp>


class SQL3 {
public:
    SQL3() {
        /*
         flags:
        SQLITE_OPEN_NOMUTEX: 设置数据库连接运行在多线程模式(没有指定单线程模式的情况下)
        SQLITE_OPEN_FULLMUTEX：设置数据库连接运行在串行模式。
        SQLITE_OPEN_SHAREDCACHE：设置运行在共享缓存模式。
        SQLITE_OPEN_PRIVATECACHE：设置运行在非共享缓存模式。
        SQLITE_OPEN_READWRITE：指定数据库连接可以读写。
        SQLITE_OPEN_CREATE：如果数据库不存在，则创建。
         * */
        int result = sqlite3_open_v2(m_path, &m_sql,
                                     SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_NOMUTEX|SQLITE_OPEN_SHAREDCACHE,
                                     nullptr);
        if (SQLITE_OK == result) {
            std::cout << "SQLite3 打开成功" << std::endl;
        } else {
            std::cout << "SQLite3 打开失败" << std::endl;
        }
    }
    ~SQL3(){
        sqlite3_close_v2(m_sql);
    }

public:
    void create_table() {
        const char* sql_sentence = "CREATE TABLE IF NOT EXISTS [Persons] ([name] VARCHAR NOT NULL,[age] INT NULL);";
        this->exec(sql_sentence);
    }
    void insert() {
        const char* sql_sentence1 = "INSERT INTO Persons(name, age) VALUES('Trunk', 4);";
        this->exec(sql_sentence1);
        const char* sql_sentence2 = "INSERT INTO Persons(name, age) VALUES('Master', 6);";
        this->exec(sql_sentence2);
    }
    void update() {
        const char* sql_sentence = "UPDATE Persons set age=8 where name='Master'";
        this->exec(sql_sentence);
    }
    void del() {
        const char* sql_sentence = "delete from Persons where name='Master'";
        this->exec(sql_sentence);
    }
    nlohmann::json get() {
        nlohmann::json data;
        const char* sql_sentence = "select name,age from Persons where age<10";
        sqlite3_stmt* stmt = nullptr;
        int result = sqlite3_prepare_v2(m_sql, sql_sentence, -1, &stmt, nullptr);
        if (SQLITE_OK == result) {
            while (SQLITE_ROW == sqlite3_step(stmt)) {
                const unsigned char* name = sqlite3_column_text(stmt, 0);
                int age = sqlite3_column_int(stmt, 1);
                data[(char*)name] = age;
            }
        } else {
            std::cout << "添加数据语句有问题" << std::endl;
        }
        sqlite3_finalize(stmt);
        return data;
    }
private:
    int exec(const char* s) {
        sqlite3_stmt* stmt = nullptr; // 执行stmt句柄 如果指令能查询到下一行数据，就会返回SQLITE_ROW; 如果指令（例如写入数据）不需要返还数据，就会返还SQLITE_DONE
        int result = sqlite3_prepare_v2(m_sql, s, -1, &stmt, nullptr); // 检查SQL语句的合法性
        if (SQLITE_OK == result) {
            sqlite3_step(stmt);
        } else {
            std::cout << "添加数据语句有问题" << std::endl;
        }
        sqlite3_finalize(stmt); // 清理语句句柄
        return result;
    }
    sqlite3* m_sql = nullptr;         // 一个打开的数据库实例
    const char* m_path = "../test.db";//某个sql文件的路径

};

int main() {
    std::cout << "Hello, SQLite3!" << std::endl;
    SQL3 sql;
    sql.create_table();
    sql.insert();
    sql.update();
//    sql.del();
    std::cout << sql.get() << std::endl;
    return 0;
}

from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import sessionmaker

engine = create_engine('sqlite:///test.db', echo=True)
Base = declarative_base(engine)


class User(Base):

    __tablename__ = 'users'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(20))
    password = Column(String(32))


Base.metadata.create_all()

DBSession = sessionmaker(bind=engine)
session = DBSession()


class SQL3(object):

    def __init__(self):
        pass

    def insert(self):
        user = User(name='Trunk', password='qwe')
        session.add(user)
        session.commit()
        return None


if __name__ == '__main__':
    print("Hello SQLAlchemy!")
    sql = SQL3()

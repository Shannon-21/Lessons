from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.orm import sessionmaker, declarative_base

engine = create_engine('sqlite:///sqlalchemy_example.db')

Base = declarative_base()

class Book(Base):
    __tablename__ = 'books'

    id = Column(Integer, primary_key=True)
    title = Column(String(250), nullable=False)
    author = Column(String(250), nullable=False)
    genre = Column(String(100))

    def __repr__(self):
        return f"<Book(title='{self.title}', author='{self.author}', genre='{self.genre}')>"
    
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

new_book = Book(title='A', author='a', genre='a')
session.add(new_book)
session.commit()

book = session.query(Book).filter_by(title='A').first()
print(book)

session.close()
from sqlalchemy import func
from sqlalchemy import ForeignKey
from sqlalchemy.orm import joinedload, sessionmaker
from sqlalchemy.orm import relationship, declarative_base
from sqlalchemy import Column, Integer, String, create_engine

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'

    id = Column(Integer, primary_key=True)
    name = Column(String)
    fullname = Column(String)
    email = Column(String)

    def __repr__(self):
        return f"<User(name='{self.name}', fullname='{self.fullname}', email='{self.email}')>"

class Address(Base):
    __tablename__ = 'addresses'

    id = Column(Integer, primary_key=True)
    email_address = Column(String, nullable=False)
    user_id = Column(Integer, ForeignKey('users.id'))

    user = relationship("User", back_populates="addresses")

User.addresses = relationship("Address", order_by=Address.id, back_populates="user")

engine = create_engine('sqlite:///example.db')
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

new_user = User(name='ed', fullname='Ed Jones', email='ed@example.com')
session.add(new_user)
session.commit()

new_address = Address(email_address='ed@gmail.com', user_id='1')
session.add(new_address)
session.commit()

# Fetch all users
users = session.query(User).all()

# Fetch a specific user
user = session.query(User).filter_by(name='ed').first()

user = session.query(User).filter_by(name='ed').first()
user.fullname = 'Edward Jones'
session.commit()

user = session.query(User).filter_by(name='ed').first()
session.delete(user)
session.commit()

# Select all users
users = session.query(User).all()

# Select users with a specific name
users = session.query(User).filter_by(name='ed').all()

# Select users with names starting with 'ed'
users = session.query(User).filter(User.name.like('ed%')).all()

users = session.query(User).limit(5).all()

results = session.query(User, Address).join(Address).all()

# Count the number of users
user_count = session.query(func.count(User.id)).scalar()

# Get the user with the most addresses
user_with_most_addresses = session.query(User, func.count(Address.id).label('address_count')).\
    join(Address).\
    group_by(User).\
    order_by(func.count(Address.id).desc()).\
    first()

from sqlalchemy import Subquery

# Get users with more than 2 addresses
address_count = session.query(Address.user_id, func.count('*').label('address_count')).\
    group_by(Address.user_id).\
    subquery()

users = session.query(User).\
    join(address_count, User.id == address_count.c.user_id).\
    filter(address_count.c.address_count > 2).\
    all()

users = session.query(User).options(joinedload(User.addresses)).all()

session.close()
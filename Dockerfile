FROM python:3.7-slim

RUN apt-get update
RUN apt-get install -y python3-dev build-essential cmake git

WORKDIR /usr/src/app

COPY *.cpp *.h *.py CMakeLists* requirements.txt ./

COPY english-words ./english-words
COPY pybind11 ./pybind11

RUN pip install -r requirements.txt

RUN python setup.py install

EXPOSE 8080

CMD ["gunicorn", "server:app"]
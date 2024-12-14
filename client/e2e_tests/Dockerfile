FROM python:3.10.2
LABEL name="End-to-end tests"
LABEL authors="Eden Kfir Avi"
LABEL version="0.1"

WORKDIR /app
COPY . .

# Run tests
CMD ["python", "e2e_tests.py"]

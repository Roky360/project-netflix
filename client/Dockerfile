FROM python:3.10.2
LABEL name="Client"
LABEL authors="Eden Kfir Avi"
LABEL version="0.1"

WORKDIR /app
COPY . .

# Accept the server IP and port
ARG IP
ARG PORT
ENV IP=${IP}
ENV PORT=${PORT}

# Run the client main with provided arguments
CMD ["sh", "-c", "python client.py $IP $PORT"]
#CMD ["python", "client.py", "$IP", "$PORT"]

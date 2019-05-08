### Create the CADG Apache web frontend image

# Get base apache image from Docker Hub
FROM httpd:2.4

# Install VIM editor for configuration changes inside the machine 
# This is not the recommended way to do it, its best to configure the file first.
# However, it may be necessary to modify depending on the server.
RUN apt-get update
RUN apt-get install vim -y \
	nano

# Copy apache configuration file into the Docker
COPY "./apache_config/" "/usr/local/apache2/conf"

# Copy any HTML files to be served locally into the Docker
COPY "./html_files/" "/usr/local/apache2/htdocs/"

RUN mkdir "/usr/local/ssl_cert"

COPY "./ssl_cert/" "/usr/local/ssl_cert"

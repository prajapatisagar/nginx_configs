	try_files $uri =404;
	fastcgi_split_path_info ^(.+\.php)(/.+)$;
	#NOTE: You should have "cgi.fix_pathinfo = 0;" in php.ini

	include /etc/nginx/fastcgi_params;
	fastcgi_pass unix:/run/php/php7.2-fpm.sock;
	fastcgi_index index.php;
	fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;

	#don't serve pages defined earlier
	fastcgi_cache_bypass $no_cache;

	#don't cache pages defined earlier
	fastcgi_no_cache $no_cache;

	#unsure what the impacts of this variable is
	fastcgi_max_temp_file_size 2M;

	#Use stale cache items while updating in the background
	fastcgi_cache_use_stale updating error timeout invalid_header http_500;
	fastcgi_cache_lock on;
	fastcgi_cache_lock_timeout 10s;

	add_header X-Cache $upstream_cache_status;

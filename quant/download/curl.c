int	download(CURL *session, char *url, char *name)
{
	FILE *file;

	file = fopen(name, "w");
	curl_easy_setopt(session, CURLOPT_URL, url);
	curl_easy_setopt(session, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, fwrite);
	if (curl_easy_perform(session) != 0)
		return -1;
	fclose(file);
	return 0;
}

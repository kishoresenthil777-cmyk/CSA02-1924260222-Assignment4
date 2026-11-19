
int shared_token = 1000;

int next_external_token(void) {
    return ++shared_token;
}

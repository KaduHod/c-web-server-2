SERVER_URI=http://localhost:9999

curl "$SERVER_URI/" -H 'Content-type: application/json'	-H 'Authorization: Bearer asdf##2@@' -d '{"name":"carlos","age":"25","job":"software-developer"}'

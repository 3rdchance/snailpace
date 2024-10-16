if [ $# -ne 1 ]
then
	echo "Usage: $0 key"
	exit
fi

GIT_SSH_COMMAND="ssh -o IdentitiesOnly=yes  -i $1  -F /dev/null -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no" git push

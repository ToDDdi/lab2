label1() {
echo "============================================================="
echo "Выберите команду:"
echo "1. Все процессы"
echo "   a.Идентификатор процесса в системе"
echo "   b.Информация о владельце процесса"
echo "   c.Процессы, не привязанные к текущему терминалу"
echo "2.Процессы текущего пользователя"
echo "3.Дерево процессов и их идентификаторы"
echo "4.Зомби процессы"
echo "5.Закончить"

read keypress
case $keypress in
    1) 
        ps -aux
        label1
        ;;
    2) 
        ps -au
        label1
        ;;
    3)
        ps -fax
        label1
        ;;      
    4) 
        label2
        ;;
    5)
        exit
	;;
esac
}

label2() {
echo "============================================================="
echo "1.Показать на экране"
echo "2.Убить зомби процессы"
echo "3.Вернуться"
read zombie
case $zombie in
    1)
        ps aux |grep -w Z
        label2
        ;;
    2)
        my_array=($(ps ajx|grep -w Z|gawk '{print $3}'))
        my_array_length=${#my_array[@]}
        for((i = 0; i < $my_array_length;i++))
        do 
        kill -9 ${my_array[i]}
	done
        ;;
    3)
        label1
	;;
esac
}

label1

//Археолог нашел N артефактов.Известны веса(сi) и объемы(di) артефактов.Нужно
//выбрать такое подмножество найденных вещей, чтобы суммарный их вес находился в пределах
//от A до B кг, а их общий объем оказался минимальным.Известно, что решение единственно.
//Укажите порядковые номера вещей, которые надо взять.Исходный данные находятся в текстовом 
//файле, в первой строке указаны N, А и B, а во второй строке значения весов(в кг), в третьей
//объемы находок(в куб.см).Вывести так же суммарный вес и объем результата.

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>

// using namespace std; // FIX_MEOW: используется глобальный using namespace std

// FIX_MEOW: отсутствие поясняющих комментариев

// FIX_MEOW: неправильное расположение фигурных скобок

// void BackRec4() { // FIX_MEOW: некорректное название функции
void SolveArtefacts()
{
    std::ifstream f("f.txt");
    if (!f.is_open())
    // FIX_MEOW: отсутствие выхода при ошибке открытия файла
    {
        std::cout << "Файл не найден." << std::endl;
        return;
    }
    else 
    {
        int N, A, B;
        f >> N >> A >> B;

        // std::vector<int> c(N), d(N); // FIX_MEOW: некорректное название векторов
        std::vector<int> WeightCi(N), VolumeDi(N);
        // for (int i = 0; i < N; i++) FIX)_MEOW: некорректное название переменной
        for (int Index = 0; Index < N; Index++)
        {
            f >> WeightCi[Index];
        }
        for (int Index = 0; Index < N; Index++)
        {
            f >> VolumeDi[Index];
        }

        f.close();

        // std::vector<int> dp(B + 1, INT_MAX); // FIX_MEOW: некорректное название вектора
        std::vector<int> MinWeight(B + 1, INT_MAX);
        MinWeight[0] = 0;
        for (int Index = 0; Index < N; Index++)
        {
            // for (int w = B; w >= WeightCi[i]; w--) FIX_MEOW: некорректное название переменной
            for (int Weight = B; Weight >= WeightCi[Index]; Weight--)
            {
                if (MinWeight[Weight - WeightCi[Index]] != INT_MAX)
                {
                    MinWeight[Weight] = std::min(MinWeight[Weight], MinWeight[Weight - WeightCi[Index]] + VolumeDi[Index]);
                }
            }
        }

        // int min_d = INT_MAX; FIX_MEOW: некорректное название переменной
        int MinD = INT_MAX;
        // int C = 0; FIX_MEOW: некорректное название переменной
        int ResultWeight = 0;
        for (int CurrentWeight = A; CurrentWeight <= B; CurrentWeight++)
        {
            if (MinWeight[CurrentWeight] < MinD)
            {
                MinD = MinWeight[CurrentWeight];
                ResultWeight = CurrentWeight;
            }
        }

        if (MinD == INT_MAX)
        {
            // std::cout << ":"; FIX_MEOW: некорректное сообщение об отсутствии решения
            std::cout << "Решение отсутствует" << std::endl;
        }
        else {
            std::cout << "Минимальный объём: " << MinD << std::endl;
            std::cout << "Вес: " << ResultWeight << std::endl;
            std::cout << "Артефакты:" << std::endl;

            int CurrentWeight = ResultWeight;
            for (int i = N - 1; i >= 0; i--)
            {
                // if (w >= c[i] and dp[w] == dp[w - c[i]] + d[i]) { // FIX_MEOW: используется and вместо &&
                if (CurrentWeight >= WeightCi[i] && MinWeight[CurrentWeight] == MinWeight[CurrentWeight - WeightCi[i]] + VolumeDi[i])
                {
                    std::cout << i + 1 << ") Вес: " << WeightCi[i] << " Объём: " << VolumeDi[i] << std::endl;
                    CurrentWeight -= WeightCi[i];
                }
            }
        }

    }

}

int main()
{
    setlocale(LC_ALL, "ru");
    SolveArtefacts(); std::cout << std::endl << std::endl;
}
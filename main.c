#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void generateArray(int arr[], int n)
{
    srand((unsigned)time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}
void equateToOriginalArray(int OriginalArr[], int Arr[], int n)
{
    int i, j = 0;
    for(i = 0; i < n; i++)
    {
        Arr[i] = OriginalArr[j];
        j++;
    }
}
void selectionSort(int arr[], int n)
{
    int i, j, min;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        if(i != min)
            swap(&arr[min], &arr[i]);
    }
}

void insertionSort(int arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
void merge(int arr[], int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1;
    int n2 =  r - q;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j];
    i = 0;
    j = 0;
    k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int p, int r)
{
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}
void MaxHeapify(int arr[], int n, int i) {
    int root = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[root])
        root = left;

    if (right < n && arr[right] > arr[root])
        root = right;

    if (root != i) {
        swap(&arr[i], &arr[root]);
        MaxHeapify(arr, n, root);
    }
}
void heapSort(int arr[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--)
        MaxHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        MaxHeapify(arr, i, 0);
    }
}

void quickSort(int arr[], int p, int r) {

    int pivot = arr[(p + r)/2];
    int i = p;
    int j = r;

    do {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (p < j) quickSort(arr, p, j);
    if (i < r) quickSort(arr, i, r);
}

int main()
{
    int a[5] = {1000, 5000, 10000, 50000, 100000};
    for(int i = 0; i < 5; i++)
    {
        int* originalArray = malloc(a[i]* sizeof(int));                        // to prevent the occurrence of stack overflow
        int* newArray = malloc(a[i]* sizeof(int));                            // new array to use for the purpose of keeping the original array as it is
        generateArray(originalArray, a[i]);
        equateToOriginalArray(originalArray, newArray, a[i]);                       // equating the new array to the original array  (newArray = originalArray)
        printf("\n--------------------------------------------------------------------------------------\n");
        printf("Sorting an Array of %d elements...",a[i]);
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        insertionSort(newArray, a[i]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Insertion Sort = %.1f milli-seconds", cpu_time_used * 1000);
        equateToOriginalArray(originalArray, newArray, a[i]);                      // returning the new sorted array to the original unsorted array
        start = clock();
        selectionSort(newArray, a[i]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Selection Sort = %.1f milli-seconds", cpu_time_used * 1000);
        equateToOriginalArray(originalArray, newArray, a[i]);                   // returning the new sorted array to the original unsorted array
        start = clock();
        bubbleSort(newArray, a[i]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Bubble Sort = %.1f milli-seconds", cpu_time_used * 1000);
        equateToOriginalArray(originalArray, newArray, a[i]);                  // returning the new sorted array to the original unsorted array
        start = clock();
        mergeSort(newArray, 0, a[i] - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Merge Sort = %.1f milli-seconds", cpu_time_used * 1000);
        equateToOriginalArray(originalArray, newArray, a[i]);                 // returning the new sorted array to the original unsorted array
        start = clock();
        heapSort(newArray, a[i]);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Heap Sort = %.1f milli-seconds", cpu_time_used * 1000);
        equateToOriginalArray(originalArray, newArray, a[i]);                 // returning the new sorted array to the original unsorted array
        start = clock();
        quickSort(newArray, 0, a[i] - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC ;
        printf("\nTime taken for Quick Sort = %.1f milli-seconds", cpu_time_used * 1000);
        free(originalArray);
        free(newArray);
    }


    return 0;
}
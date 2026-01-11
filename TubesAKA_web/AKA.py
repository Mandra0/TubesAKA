from flask import Flask, render_template, request, jsonify
import time, random, sys

app = Flask(__name__)
sys.setrecursionlimit(10000)

def insertion_sort(arr, left, right):
    for i in range(left + 1, right + 1):
        key, j = arr[i], i - 1
        while j >= left and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def merge(arr, l, m, r):
    left_part = arr[l:m+1]
    right_part = arr[m+1:r+1]
    i = j = 0
    k = l
    while i < len(left_part) and j < len(right_part):
        if left_part[i] <= right_part[j]:
            arr[k] = left_part[i]; i += 1
        else:
            arr[k] = right_part[j]; j += 1
        k += 1
    while i < len(left_part): arr[k] = left_part[i]; i += 1; k += 1
    while j < len(right_part): arr[k] = right_part[j]; j += 1; k += 1

def merge_sort(arr, l, r):
    if l < r:
        m = (l + r) // 2
        merge_sort(arr, l, m)
        merge_sort(arr, m + 1, r)
        merge(arr, l, m, r)

def hybrid_sort(arr, l, r, k):
    if (r - l + 1) <= k:
        insertion_sort(arr, l, r)
    elif l < r:
        m = (l + r) // 2
        hybrid_sort(arr, l, m, k)
        hybrid_sort(arr, m + 1, r, k)
        merge(arr, l, m, r)

@app.route('/')
def home(): 
    return render_template('index.html')

@app.route('/api/analyze_single', methods=['POST'])
def analyze_single():
    data = request.get_json()
    n = int(data.get('n', 500))
    k = int(data.get('k', 32))
    
    base = [random.randint(1, 10000) for _ in range(n)]
    
    # 1. Iterative (Insertion)
    d1 = list(base); s1 = time.perf_counter()
    insertion_sort(d1, 0, n-1)
    t1 = (time.perf_counter() - s1) * 1000

    # 2. Recursive (Merge)
    d2 = list(base); s2 = time.perf_counter()
    merge_sort(d2, 0, n-1)
    t2 = (time.perf_counter() - s2) * 1000

    # 3. Hybrid
    d3 = list(base); s3 = time.perf_counter()
    hybrid_sort(d3, 0, n-1, k)
    t3 = (time.perf_counter() - s3) * 1000

    return jsonify({"iter": t1, "rec": t2, "hyb": t3})

if __name__ == '__main__': 
    app.run(debug=True)
    import os
    port = int(os.environ.get("PORT", 5000))
    app.run(host='0.0.0.0', port=port)
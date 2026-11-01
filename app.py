from flask import Flask, render_template, request, redirect, url_for, jsonify
from algorithms import MemoryManager, PagingSimulator
import json

app = Flask(__name__)

@app.route('/')
def index():
return render_template('index.html')

@app.route('/simulate_allocation', methods=['POST'])
def simulate_allocation():
data = request.get_json()
# data contains: memory_size, holes (list of (start,size)), processes list (id,size), algorithm
mm = MemoryManager(memory_size=data['memory_size'], holes=data.get('holes', []))
alg = data.get('algorithm', 'first_fit')
result = mm.run_allocation(processes=data['processes'], algorithm=alg)
return jsonify(result)

@app.route('/simulate_paging', methods=['POST'])
def simulate_paging():
data = request.get_json()
ps = PagingSimulator(frame_count=data['frames'], reference_string=data['refs'])
policy = data.get('policy', 'fifo')
res = ps.run(policy=policy)
return jsonify(res)

@app.route('/ui')
def ui():
return render_template('simulate.html')

if __name__ == '__main__':
app.run(debug=True)
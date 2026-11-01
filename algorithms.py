import copy
def __init__(self, frame_count=4, reference_string=None):
self.frames = frame_count
self.refs = reference_string or []

def run(self, policy='fifo'):
if policy == 'fifo':
return self._fifo()
elif policy == 'lru':
return self._lru()
elif policy == 'optimal':
return self._optimal()
else:
return {'error':'Unknown policy'}

def _fifo(self):
frames = deque()
hits = 0
timeline = []
for r in self.refs:
if r in frames:
hits += 1
else:
if len(frames) < self.frames:
frames.append(r)
else:
frames.popleft(); frames.append(r)
timeline.append({'ref':r,'frames':list(frames)})
return {'policy':'fifo','timeline':timeline,'hits':hits,'faults':len(self.refs)-hits}

def _lru(self):
frames = []
usage = {} # page -> last index
hits = 0
timeline = []
for i,r in enumerate(self.refs):
if r in frames:
hits += 1
else:
if len(frames) < self.frames:
frames.append(r)
else:
# evict least recently used
lru_page = min(frames, key=lambda p: usage.get(p, -1))
idx = frames.index(lru_page)
frames[idx] = r
usage[r] = i
timeline.append({'ref':r,'frames':list(frames)})
return {'policy':'lru','timeline':timeline,'hits':hits,'faults':len(self.refs)-hits}

def _optimal(self):
frames = []
hits = 0
timeline = []
for i,r in enumerate(self.refs):
if r in frames:
hits += 1
else:
if len(frames) < self.frames:
frames.append(r)
else:
# choose page with farthest next use
farthest = -1
replace_idx = 0
for idx,p in enumerate(frames):
try:
nxt = self.refs.index(p, i+1)
except ValueError:
nxt = float('inf')
if nxt > farthest:
farthest = nxt; replace_idx = idx
frames[replace_idx] = r
timeline.append({'ref':r,'frames':list(frames)})
return {'policy':'optimal','timeline':timeline,'hits':hits,'faults':len(self.refs)-hits}
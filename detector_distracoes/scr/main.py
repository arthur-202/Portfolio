import cv2
import mediapipe as mp
import math
import numpy as np

# Função auxiliar para calcular distância
def dist(p1, p2):
    return math.hypot(p2[0] - p1[0], p2[1] - p1[1])

# Configurações do Face Mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(
    max_num_faces=1,
    refine_landmarks=True,
    min_detection_confidence=0.6,
    min_tracking_confidence=0.6
)

# Constantes ajustadas
EAR_THRESHOLD = 0.21
MOUTH_THRESHOLD = 0.085
EYEBROW_THRESHOLD = 0.07
HEAD_DROP_THRESHOLD = 0.18
CONFIDENCE_FRAMES = 8

class FocusDetector:
    def __init__(self):
        self.face_reference = 0
        self.ear_history = []
        self.status = "Analisando..."
        self.confidence = 0
        self.calibrated = False
        
    def update_status(self, ear, mouth_open, eyebrow_drop, head_drop):
        eye_status = ear < EAR_THRESHOLD
        mouth_status = mouth_open > MOUTH_THRESHOLD
        eyebrow_status = eyebrow_drop > EYEBROW_THRESHOLD
        head_status = head_drop > HEAD_DROP_THRESHOLD
        
        if eye_status or mouth_status or (eyebrow_status and head_status):
            self.confidence = max(self.confidence - 2, -CONFIDENCE_FRAMES)
        elif not any([eye_status, mouth_status, eyebrow_status, head_status]):
            self.confidence = min(self.confidence + 1, CONFIDENCE_FRAMES)
        else:
            self.confidence = max(self.confidence - 1, -CONFIDENCE_FRAMES)
        
        if self.confidence >= CONFIDENCE_FRAMES:
            self.status = "Focado ✅"
        elif self.confidence <= -CONFIDENCE_FRAMES:
            self.status = "Desfocado ❌"
        else:
            self.status = "Neutro ➖"

def eye_aspect_ratio(eye_points):
    return (dist(eye_points[1], eye_points[5]) + dist(eye_points[2], eye_points[4])) / (2 * dist(eye_points[0], eye_points[3]))

# Inicialização
detector = FocusDetector()
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(frame_rgb)

    if results.multi_face_landmarks:
        landmarks = results.multi_face_landmarks[0].landmark
        h, w = frame.shape[:2]
        points = [(int(lm.x * w), int(lm.y * h)) for lm in landmarks]
        
        face_size = math.hypot(points[10][0]-points[152][0], points[10][1]-points[152][1])
        
        left_eye = [points[i] for i in [33, 159, 158, 133, 153, 144]]
        right_eye = [points[i] for i in [362, 386, 387, 263, 373, 380]]
        ear = (eye_aspect_ratio(left_eye) + eye_aspect_ratio(right_eye)) / 2
        
        mouth_open = dist(points[13], points[14]) / face_size
        eyebrow_drop = (points[159][1] - points[70][1]) / face_size
        head_drop = (points[1][1] - points[0][1]) / face_size
        
        if not detector.calibrated and detector.face_reference == 0:
            detector.face_reference = face_size
            detector.calibrated = True
        
        detector.update_status(ear, mouth_open, eyebrow_drop, head_drop)
        
        color = (0, 255, 0) if "Focado" in detector.status else (0, 0, 255) if "Desfocado" in detector.status else (255, 255, 0)
        cv2.putText(frame, detector.status, (30, 60), cv2.FONT_HERSHEY_SIMPLEX, 1.3, color, 3)
        
        cv2.putText(frame, f"Olhos: {ear:.2f}", (30, 110), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 1)
        cv2.putText(frame, f"Boca: {mouth_open:.3f}", (30, 140), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 1)
        
        if "Desfocado" in detector.status:
            cv2.rectangle(frame, (0, 0), (w, h), (0, 0, 255), 10)
            cv2.putText(frame, "ALERTA: Foco perdido!", (w//4, h-30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    
    cv2.imshow("Monitor de Foco Inteligente", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
